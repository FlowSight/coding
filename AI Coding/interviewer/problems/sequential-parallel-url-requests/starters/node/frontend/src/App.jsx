import { useState } from 'react';
import { runSequentialRequests } from './api.js';
import { RequestResults } from './components/RequestResults.jsx';

export default function App() {
  const [input, setInput] = useState('https://example.com\nhttps://example.org');
  const [results, setResults] = useState([]);
  const [error, setError] = useState('');
  async function submit(event) {
    event.preventDefault();
    try {
      const urls = input.split('\n').map((url) => url.trim()).filter(Boolean);
      setResults((await runSequentialRequests(urls)).results);
      setError('');
    } catch (cause) {
      setError(cause.message);
    }
  }
  return <main><h1>URL request scheduler</h1>
    <form onSubmit={submit}>
      <textarea rows="7" value={input} onChange={(event) => setInput(event.target.value)} />
      <button>Run sequentially</button>
    </form>
    {error && <p role="alert">{error}</p>}
    <RequestResults results={results} />
  </main>;
}
