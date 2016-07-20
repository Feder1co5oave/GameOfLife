String.prototype.firstUpper = () -> @charAt(0).toUpperCase() + @slice(1)

google.charts.load('current', packages: ['corechart'])

generate_charts = (bm) ->
	sets =
		mic:
			'4000-TH': bm.mic._4000x1000.threads
			'4000-FF': bm.mic._4000x1000.fastflow
			#'4000-FF_nospin': bm.mic._4000x1000.fastflow_no_spin
			'8000-TH': bm.mic._8000x1000.threads
			'8000-FF': bm.mic._8000x1000.fastflow
			#'8000-FF_nospin': bm.mic._8000x1000.fastflow_no_spin
		xeon:
			'4000-TH': bm.xeon._4000x1000.threads
			'4000-FF': bm.xeon._4000x1000.fastflow
			'8000-TH': bm.xeon._8000x1000.threads
			'8000-FF': bm.xeon._8000x1000.fastflow

	google.charts.setOnLoadCallback () ->
		for _s,subsets of sets
			every_set = (map) ->
				(map set for s,set of subsets)
			every_size = (map) ->
				results = []
				results = results.concat map size_set for size,size_set of bm[_s]
				results

			tables = 
				times: new google.visualization.DataTable()
				speedup: new google.visualization.DataTable()
				scalability: new google.visualization.DataTable()
				efficiency: new google.visualization.DataTable()

			for k,table of tables
				table.addColumn('number', 'threads')
				table.addColumn('number', set) for set of subsets

			min = 9999999
			max = -1
			for i in [0..bm[_s]._4000x1000.threads.length-1]
				p = bm[_s]._4000x1000.threads[i][0]
				min = Math.min(min, p)
				max = Math.max(max, p)
				tables.times.addRows [ [p].concat every_set (set) -> set[i][1] ]
				tables.scalability.addRows [ [p].concat every_set (set) -> set[0][1] / set[i][1] ]
				tables.efficiency.addRows [ [p].concat every_set (set) -> set[0][1] / set[i][1] / p ]
				tables.speedup.addRows [ [p].concat every_size (size) ->
					[ size.sequential[0][1] / size.threads[i][1],
					  size.sequential[0][1] / size.fastflow[i][1] ]
				]

			tables.timings = { }

			for s,set of subsets
				ss = "#{_s}_#{s}"
				table = tables.timings[ss] = new google.visualization.DataTable()
				table.addColumn('number', 'x')
				table.addColumn('number', 'avg')
				table.addColumn {id: 'i'+i, type: 'number', role: 'interval'} for i in [1..set[0].length - 2]
				table.addRows set
				if div = document.getElementById "#{ss}_timings_chart"
					chart = new google.visualization.LineChart div
					chart.draw(table,
						title: "#{_s} #{s}".firstUpper()
						subtitle: 'Timings'
						intervals: style: 'bars'
						hAxis: title: 'threads'
						vAxis:
							minValue: 0,
							title: 'time (s)'
					)
			for t,table of tables
				if div = document.getElementById "#{_s}_#{t}_chart"
					chart = new google.visualization.LineChart div
					chart.draw(table,
						title: "#{_s} #{t}".firstUpper()
						hAxis: title: 'threads'
						vAxis:
							minValue: 0
							title: t
						pointsVisible: true
						pointSize: 4
						explorer:
							actions: ['dragToZoom', 'rightClickToReset']
							keepInBounds: true
					)

	sets2 =
		mic:
			novec: bm.mic_no_vec._4000x1000.threads
			default: bm.mic._4000x1000.threads
		xeon:
			novec: bm.xeon_no_vec._4000x1000.threads
			default: bm.xeon_sse2._4000x1000.threads
			avx: bm.xeon._4000x1000.threads

	google.charts.setOnLoadCallback () ->
		data = new google.visualization.DataTable()
		data.addColumn('string', 'architecture-size-parallelism')
		data.addColumn('number', 'No vect')
		data.addColumn('number', 'Default')
		data.addColumn('number', 'AVX')

		for arch,subset of sets2
				arch = arch.firstUpper()
				cells = 4000 * 4000 * 1000
				minp = subset.novec[0][0]
				last = subset.novec.length-1
				maxp = subset.novec[last][0]
				data.addRows [
					[
						"#{arch} #{minp}th",
						cells / subset.novec[0][1],
						cells / subset.default[0][1],
						if subset.avx? then cells / subset.avx[0][1] else 0
					],  [
						"#{arch} #{maxp}th",
						cells / subset.novec[last][1],
						cells / subset.default[last][1],
						if subset.avx? then cells / subset.avx[last][1] else 0
					]
				]

		chart = new google.visualization.ColumnChart(document.getElementById 'vectorization_speedup')
		chart.draw(data,
			title: 'Vectorization speedup',
			hAxis: title: 'Architecture, parallelism degree'
			vAxis:
				title: 'Cells per second (higher is better)'
				format: 'scientific'
				gridlines: count: 10
		)

ajax(
	url: 'benchmarks.json'
	dataType: 'json'
	success: generate_charts
)