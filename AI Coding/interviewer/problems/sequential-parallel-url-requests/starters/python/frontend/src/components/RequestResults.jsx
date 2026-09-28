export default function RequestResults({ results }) {
  return <ul>{results.map((result) => <li key={result.url}>
    {result.url}: {result.error || result.status_code}
  </li>)}</ul>;
}
