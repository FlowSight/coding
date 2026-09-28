export default function ShardTable({ summaries }) {
  return <table><thead><tr><th>Shard</th><th>Latency</th><th>Requests</th><th>Errors</th></tr></thead>
    <tbody>{summaries.map((item) => <tr key={item.shard}><td>{item.shard}</td>
      <td>{item.average_latency_ms}</td><td>{item.requests}</td><td>{item.errors}</td></tr>)}</tbody></table>;
}
