const fs = require( 'fs' );
const { fetchHttpStatusCodesList, httpStatusCodesFilePath } = require('./httpStatusCodes');

let log = console;

const main = async () => {
	try
	{
		log.info( 'Updating HTTP Status Codes in file', httpStatusCodesFilePath, '...' );
		const httpStatusCodes = await fetchHttpStatusCodesList();
		fs.writeFileSync( httpStatusCodesFilePath, httpStatusCodes.httpStatusCodesList, 'utf-8' );
	}
	catch( reason ) {
		log.error( reason );
		process.exitCode = -1;
	};
};

main();
