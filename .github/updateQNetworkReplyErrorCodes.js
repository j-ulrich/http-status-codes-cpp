const fs = require( 'fs' );
const { fetchQNetworkReplyErrorCodeListFromQt, qNetworkReplyErrorCodesFilePath } = require('./qNetworkReplyErrorCodes');

let log = console;

const main = async () => {
	try
	{
		log.info( 'Updating QNetworkReply Error Codes in file', qNetworkReplyErrorCodesFilePath, '...' );
		const qNetworkReplyErrorCodes = await fetchQNetworkReplyErrorCodeListFromQt();
		fs.writeFileSync( qNetworkReplyErrorCodesFilePath, qNetworkReplyErrorCodes, 'utf-8' );
	}
	catch( reason ) {
		log.error( reason );
		process.exitCode = -1;
	};
};

main();
