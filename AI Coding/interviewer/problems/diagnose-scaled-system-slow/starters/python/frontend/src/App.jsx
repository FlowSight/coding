import { useState } from "react";
import { aggregateSamples } from "./api";
import ShardTable from "./components/ShardTable";

export default function App() {
  const [samples, setSamples] = useState('[{"shard":"a","latency_ms":20,"requests":100,"errors":0}]');
  const [summaries, setSummaries] = useState([]);
  async function submit(event) {
    event.preventDefault();
    setSummaries(await aggregateSamples(JSON.parse(samples)));
  }
  return <main><h1>Shard diagnostics</h1><form onSubmit={submit}>
    <textarea rows="7" cols="65" value={samples} onChange={(e) => setSamples(e.target.value)} />
    <button>Aggregate</button></form><ShardTable summaries={summaries} /></main>;
}
