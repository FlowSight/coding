import { useState } from 'react';
import { addRoute, matchPath } from './api.js';
import { MatchCard } from './components/MatchCard.jsx';

export default function App() {
  const [pattern, setPattern] = useState('/users/:id');
  const [path, setPath] = useState('/users/42');
  const [match, setMatch] = useState(null);
  async function submit(event) {
    event.preventDefault();
    await addRoute(pattern, 'preview-handler');
    setMatch((await matchPath(path)).match);
  }
  return <main><h1>Trie route lab</h1>
    <form onSubmit={submit}>
      <label>Pattern <input value={pattern} onChange={(event) => setPattern(event.target.value)} /></label>
      <label>Path <input value={path} onChange={(event) => setPath(event.target.value)} /></label>
      <button>Add and match</button>
    </form>
    <MatchCard match={match} />
  </main>;
}
