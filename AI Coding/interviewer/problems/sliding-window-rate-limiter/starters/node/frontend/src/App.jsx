import { useState } from 'react';
import { checkRequest } from './api.js';
import { DecisionLog } from './components/DecisionLog.jsx';

export default function App() {
  const [now, setNow] = useState(100);
  const [decisions, setDecisions] = useState([]);
  async function submit(event) {
    event.preventDefault();
    const result = await checkRequest(Number(now));
    setDecisions((current) => [...current, { now, ...result }]);
  }
  return <main><h1>Rate-limit console</h1>
    <form onSubmit={submit}>
      <label>Timestamp <input type="number" value={now} onChange={(event) => setNow(event.target.value)} /></label>
      <button>Check request</button>
    </form>
    <DecisionLog decisions={decisions} />
  </main>;
}
