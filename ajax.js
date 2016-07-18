function newXHR() {
	try { return new XMLHttpRequest(); } catch(e) {}
	try { return new ActiveXObject('Msxml2.XMLHTTP'); } catch(e) {}
	try { return new ActiveXObject('Microsoft.XMLHTTP'); } catch(e) {}
	window.alert('Your browser does not support AJAX. Please, upgrade.');
	return null;
}
function serialize(data, prefix) {
	var str = [];
	for (var k in data) {
		var name = prefix ? prefix + '['+ k + ']' : k;
		var value = data[k];
		if (value === false) value = '';

		str.push(typeof value == 'object' ?
			serialize(value, name) :
			encodeURIComponent(name) + "=" + encodeURIComponent(value));
	}
	return str.join('&');
}
function dumbMerge(from, into) {
	for (var k in from)
		into[k] = from[k];

	return into;
}
function ajax(conf) {
	var defaults = {
		// url: required
		method: 'GET',
		data: {},
		dataType: 'xml',
		success: function(data, statusText) {},
		error: function(xhr, statusText) { window.alert(statusText); },
		timeout: 10000 // 10 secs
	};
	
	conf = dumbMerge(conf, defaults);
	
	var xhr = newXHR(), done = false;
	if (!xhr) return false;

	switch (conf.method) {
		case 'GET':
			var querystr = (conf.url.indexOf('?') >= 0
				? '&'
				: '?') + serialize(conf.data);
			xhr.open('GET', conf.url + querystr, true);
			break;

		case 'POST':
			xhr.open('POST', conf.url, true);
			xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
			break;

		default:
			return false;
	}

	xhr.onreadystatechange = function() {
		if (!done && this.readyState == 4) {
			done = true;
			if (this.status == 200) {
				switch (conf.dataType) {
					case 'xml':
						if (this.responseXML) conf.success(this.responseXML, this.statusText);
						else conf.error(this, 'XML parsing error!');
						break;
					case 'json':
						try {
							if (window.JSON) json = JSON.parse(this.responseText);
							else json = eval('(' + this.responseText + ')');
						} catch (e) {}
						if (typeof json != 'undefined') conf.success(json, this.statusText);
						else conf.error(this, 'JSON parsing error!');
						break;
					case 'text':
						conf.success(this.responseText, this.statusText);
				}
			} else { // this.status != 200
				// IE sets status to 12000+ when an error has happened
				conf.error(this, 'Network/server error!');
				this.abort();
			}
		}
	};

	xhr.onerror = function() {
		if (!done) conf.error(this, 'Network/server error!');
		done = true;
	};

	xhr.onabort = function() {
		if (!done) conf.error(this, 'Request aborted.');
		done = true;
	};

	switch (conf.method) {
		case 'GET':
			xhr.send();
			break;
		case 'POST':
			if (typeof FormData == 'function' && conf.data instanceof FormData) xhr.send(conf.data);
			else xhr.send(serialize(conf.data));
	}

	setTimeout(function() {
		if (!done) {
			done = true;
			xhr.abort();
			conf.error(this, 'Request timeout.');
		}
	}, conf.timeout);
}