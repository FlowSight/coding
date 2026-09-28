export default function MatchResult({ match }) {
  return <pre>{match ? JSON.stringify(match, null, 2) : "No route matched"}</pre>;
}
