import { useState } from "react";
import { addRoute, matchRoute } from "./api";
import MatchResult from "./components/MatchResult";

export default function App() {
  const [result, setResult] = useState(null);
  async function loadExample() { await addRoute("/:kind/:id", "show"); await addRoute("/users/new/settings", "settings"); setResult(await matchRoute("/users/new")); }
  return <main><h1>Route trie playground</h1><button onClick={loadExample}>Run wildcard example</button><MatchResult result={result} /></main>;
}
