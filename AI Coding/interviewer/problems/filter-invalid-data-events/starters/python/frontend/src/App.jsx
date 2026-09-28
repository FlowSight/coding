import { useState } from "react";
import { filterEvents } from "./api";
import EventResults from "./components/EventResults";

export default function App() {
  const [text, setText] = useState('[{"id":"a","type":"created","payload":{"v":"1"}}]');
  const [results, setResults] = useState([]);
  async function submit(event) {
    event.preventDefault();
    setResults(await filterEvents(JSON.parse(text)));
  }
  return <main><h1>Event validator</h1><form onSubmit={submit}>
    <textarea value={text} onChange={(e) => setText(e.target.value)} rows="8" cols="60" />
    <button>Filter events</button>
  </form><EventResults events={results} /></main>;
}
