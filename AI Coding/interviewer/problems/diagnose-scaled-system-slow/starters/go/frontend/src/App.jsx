import { useState } from "react";
import { summarizeShards } from "./api";
import ShardSummaryTable from "./components/ShardSummaryTable";

const samples = [{ shard: "cold", latencyMs: 10, requests: 100, errors: 0 }, { shard: "hot", latencyMs: 500, requests: 100, errors: 7 }];

export default function App() {
  const [summaries, setSummaries] = useState([]);
  return <main><h1>Shard diagnostics</h1><button onClick={async () => setSummaries(await summarizeShards(samples))}>Analyze samples</button><ShardSummaryTable summaries={summaries} /></main>;
}
