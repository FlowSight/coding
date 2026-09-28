export default function DecisionHistory({ history }) {
  return <ol>{history.map((item) => <li key={item.at}>{item.at}: <strong>{item.allowed ? "allowed" : "blocked"}</strong></li>)}</ol>;
}
