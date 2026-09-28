import { useState } from "react";
import { addRoute, matchPath } from "./api";
import MatchResult from "./components/MatchResult";

export default function App() {
  const [pattern, setPattern] = useState("/:kind/:id");
  const [handler, setHandler] = useState("show");
  const [path, setPath] = useState("/users/42");
  const [match, setMatch] = useState(null);
  return <main><h1>Trie route playground</h1>
    <input value={pattern} onChange={(e) => setPattern(e.target.value)} />
    <input value={handler} onChange={(e) => setHandler(e.target.value)} />
    <button onClick={() => addRoute(pattern, handler)}>Add route</button>
    <input value={path} onChange={(e) => setPath(e.target.value)} />
    <button onClick={async () => setMatch(await matchPath(path))}>Match</button>
    <MatchResult match={match} /></main>;
}
