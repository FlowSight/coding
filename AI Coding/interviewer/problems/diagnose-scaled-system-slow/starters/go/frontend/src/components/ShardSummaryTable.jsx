export default function ShardSummaryTable({ summaries }) {
  return <table><thead><tr><th>Shard</th><th>Average latency</th><th>Errors</th></tr></thead><tbody>{summaries.map((item) => <tr key={item.shard}><td>{item.shard}</td><td>{item.averageLatencyMs} ms</td><td>{item.errors}</td></tr>)}</tbody></table>;
}
