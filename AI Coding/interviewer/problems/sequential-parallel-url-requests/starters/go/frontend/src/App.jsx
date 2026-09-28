import { useState } from "react";
import { runSequential } from "./api";
import RequestResults from "./components/RequestResults";

export default function App() {
  const [text, setText] = useState("https://b.example\nhttps://a.example\nhttps://b.example");
  const [results, setResults] = useState([]);
  return <main><h1>URL request runner</h1><textarea rows="6" value={text} onChange={(event) => setText(event.target.value)} /><button onClick={async () => setResults(await runSequential(text.split("\n").filter(Boolean)))}>Run sequentially</button><RequestResults results={results} /></main>;
}
