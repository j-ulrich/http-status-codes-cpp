
const searchForExistingGithubIssue = async ( { keywords, github, context } ) => {
	const query = keywords.concat( [ 'in:title', `repo:${context.repo.owner}/${context.repo.repo}`, 'type:issue' ] ).join( '+' );
	const searchResponse = await github.search.issuesAndPullRequests( {
		q: query,
	} );
	return searchResponse.data;
};

const createNewGithubIssue = async ( { title, body, github, context } ) => {

	const newIssue = {
		owner: context.repo.owner,
		repo: context.repo.repo,
		title,
		body
	};

	const issueResponse = await github.issues.create( newIssue );
	return issueResponse.data;
};

module.exports = { searchForExistingGithubIssue, createNewGithubIssue };