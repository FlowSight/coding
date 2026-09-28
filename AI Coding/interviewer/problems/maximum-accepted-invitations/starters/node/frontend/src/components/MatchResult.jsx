export function MatchResult({ count }) {
  return <section><h2>Matching result</h2>
    <p>{count === null ? 'Calculate a matching.' : `${count} invitations can be accepted.`}</p>
  </section>;
}
