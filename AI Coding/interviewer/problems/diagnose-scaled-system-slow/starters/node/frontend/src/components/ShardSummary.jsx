export function ShardSummary({ summary }) {
  if (!summary) return <p>Submit the snapshot to begin diagnosis.</p>;
  return <section>
    <h2>Fleet summary</h2>
    <p>{summary.requests} requests at {summary.averageLatencyMs} ms average</p>
    <p>Hot shards: {summary.hotShards.join(', ') || 'none'}</p>
  </section>;
}
