import React from 'react';
export default function ShardTable({ shards }) {
  return <table><thead><tr><th>Shard</th><th>Requests</th><th>P99 ms</th><th>CPU</th></tr></thead><tbody>{shards.map(s => <tr key={s.shardId}><td>{s.shardId}</td><td>{s.requestCount}</td><td>{s.p99LatencyMillis}</td><td>{s.cpuPercent}%</td></tr>)}</tbody></table>;
}
