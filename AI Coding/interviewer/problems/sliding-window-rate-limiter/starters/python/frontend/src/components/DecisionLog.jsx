export default function DecisionLog({ decisions }) {
  return <ol>{decisions.map((item, index) =>
    <li key={index}>{item.allowed ? "Allowed" : "Rejected"} at {item.evaluated_at}</li>)}</ol>;
}
