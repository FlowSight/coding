export function RequestResults({ results }) {
  return <section><h2>Responses</h2>
    {results.length === 0 ? <p>No request job has run.</p> :
      <ol>{results.map((result, index) =>
        <li key={`${result.url}-${index}`}>{result.url}: HTTP {result.status}</li>)}</ol>}
  </section>;
}
