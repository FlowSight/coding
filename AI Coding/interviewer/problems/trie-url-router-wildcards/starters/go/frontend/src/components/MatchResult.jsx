export default function MatchResult({ result }) {
  if (!result) return null;
  return <section><h2>{result.found ? result.handler : "No match"}</h2><pre>{JSON.stringify(result.params, null, 2)}</pre></section>;
}
