export default function MatchSummary({ count }) {
  return <p>Maximum accepted invitations: <strong>{count ?? "Not calculated"}</strong></p>;
}
