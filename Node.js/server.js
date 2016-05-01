var http = require('http');
var url = require('url');

/* 
 * Callback function. 
 * Only be called when get a request.
 */
function start(route) {
	function onRequest(request, response) {
		var pathname = url.parse(request.url).pathname;
		console.log('request for ' + pathname + ' received.');

		route(pathname);	// injected function call

		response.writeHead(200, { 'Content-Type' : 'text/plain'});
		response.write('Hello World');
		response.end();
	}

	http.createServer(onRequest).listen(8080);

	console.log('server has started.');
}

exports.start = start;
