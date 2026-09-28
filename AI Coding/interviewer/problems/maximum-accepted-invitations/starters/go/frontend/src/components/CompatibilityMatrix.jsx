export default function CompatibilityMatrix({ grid }) {
  return <table><tbody>{grid.map((row, boy) => <tr key={boy}>{row.map((value, girl) => <td key={girl} title={`Boy ${boy}, girl ${girl}`}>{value ? "✓" : "—"}</td>)}</tr>)}</tbody></table>;
}
