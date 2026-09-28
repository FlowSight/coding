import { useState } from 'react';
import { calculateMaximumInvitations } from './api.js';
import { MatchResult } from './components/MatchResult.jsx';

export default function App() {
  const [input, setInput] = useState(JSON.stringify([[1, 1], [1, 0]], null, 2));
  const [count, setCount] = useState(null);
  const [error, setError] = useState('');
  async function submit(event) {
    event.preventDefault();
    try {
      setCount((await calculateMaximumInvitations(JSON.parse(input))).count);
      setError('');
    } catch (cause) {
      setError(cause.message);
    }
  }
  return <main><h1>Invitation matching planner</h1>
    <form onSubmit={submit}>
      <textarea rows="8" value={input} onChange={(event) => setInput(event.target.value)} />
      <button>Find maximum</button>
    </form>
    {error && <p role="alert">{error}</p>}
    <MatchResult count={count} />
  </main>;
}
