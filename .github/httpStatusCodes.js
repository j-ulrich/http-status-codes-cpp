
const fetch = require( 'node-fetch' );
const path = require( 'path' );

const httpStatusCodesUrl = 'https://www.iana.org/assignments/http-status-codes/http-status-codes.txt';
const httpStatusCodesFileName = 'http-status-codes.txt';
const httpStatusCodesFilePath = path.join( __dirname, httpStatusCodesFileName );

const fetchHttpStatusCodesList = async () => {
	const response = await fetch( httpStatusCodesUrl );
	if ( !response.ok ) {
		throw Error( `Error fetching HTTP status codes list: ${response.status} ${response.statusText}` );
	}
	const httpStatusCodesList = await response.text();

	const match = /Last Updated\s+(\d{4}-\d{2}-\d{2})/.exec( httpStatusCodesList );
	if ( !match ) {
		throw Error( 'Could not find "Last Updated" date in HTTP status list' );
	}
	const lastUpdated = match[ 1 ];
	return { lastUpdated, httpStatusCodesList };
};

module.exports = { fetchHttpStatusCodesList, httpStatusCodesFileName, httpStatusCodesFilePath };
