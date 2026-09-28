import { useState } from 'react';
import { filterEvents } from './api.js';
import { AcceptedEvents } from './components/AcceptedEvents.jsx';

const sample = JSON.stringify([
  { id: 'order-2', timestamp: 20, data: { total: 25 } },
  { id: 'order-1', timestamp: 10, data: { total: 40 } }
], null, 2);

export default function App() {
  const [input, setInput] = useState(sample);
  const [events, setEvents] = useState([]);
  const [error, setError] = useState('');
  async function submit(event) {
    event.preventDefault();
    try {
      setEvents((await filterEvents(JSON.parse(input))).events);
      setError('');
    } catch (cause) {
      setError(cause.message);
    }
  }
  return <main><h1>Event ingestion workbench</h1>
    <form onSubmit={submit}>
      <textarea rows="12" value={input} onChange={(event) => setInput(event.target.value)} />
      <button>Validate batch</button>
    </form>
    {error && <p role="alert">{error}</p>}
    <AcceptedEvents events={events} />
  </main>;
}
