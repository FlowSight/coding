export default function RequestResults({ results }) {
  return <ol>{results.map((result) => <li key={result.url}>{result.url}: HTTP {result.response.statusCode}</li>)}</ol>;
}
