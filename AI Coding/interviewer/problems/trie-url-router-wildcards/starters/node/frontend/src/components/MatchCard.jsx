export function MatchCard({ match }) {
  return <section><h2>Match</h2>
    <pre>{match ? JSON.stringify(match, null, 2) : 'No route matched.'}</pre>
  </section>;
}
