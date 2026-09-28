import { useState } from 'react';
import { summarizeIncident } from './api.js';
import { ShardSummary } from './components/ShardSummary.jsx';

const initialSamples = JSON.stringify([
  { shard: 'checkout-1', requests: 1, latencyMs: 900 },
  { shard: 'checkout-2', requests: 99, latencyMs: 10 }
], null, 2);

export default function App() {
  const [input, setInput] = useState(initialSamples);
  const [summary, setSummary] = useState(null);
  const [error, setError] = useState('');
  async function submit(event) {
    event.preventDefault();
    try {
      setSummary(await summarizeIncident(JSON.parse(input), 200));
      setError('');
    } catch (cause) {
      setError(cause.message);
    }
  }
  return <main>
    <h1>Scaled-system incident desk</h1>
    <form onSubmit={submit}>
      <textarea rows="12" value={input} onChange={(event) => setInput(event.target.value)} />
      <button>Analyze snapshot</button>
    </form>
    {error && <p role="alert">{error}</p>}
    <ShardSummary summary={summary} />
  </main>;
}
