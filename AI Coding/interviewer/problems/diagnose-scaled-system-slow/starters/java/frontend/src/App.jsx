import React, { useState } from 'react';
import { analyzeShards } from './api.js';
import ShardTable from './components/ShardTable.jsx';
const sample = [{ shardId: 'api-1', requestCount: 10000, p99LatencyMillis: 20, cpuPercent: 25, errorCount: 0 }, { shardId: 'api-2', requestCount: 2, p99LatencyMillis: 2000, cpuPercent: 99, errorCount: 1 }];
export default function App() {
  const [report, setReport] = useState(null); const [error, setError] = useState('');
  async function run() { try { setError(''); setReport(await analyzeShards(sample)); } catch (e) { setError(e.message); } }
  return <main><h1>Scaled System Diagnostics</h1><ShardTable shards={sample}/><button onClick={run}>Analyze telemetry</button>{error && <p>{error}</p>}{report && <pre>{JSON.stringify(report, null, 2)}</pre>}</main>;
}
