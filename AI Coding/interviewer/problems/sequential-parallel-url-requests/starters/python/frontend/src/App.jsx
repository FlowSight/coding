import { useState } from "react";
import { runRequests } from "./api";
import RequestResults from "./components/RequestResults";

export default function App() {
  const [urls, setUrls] = useState("https://example.com\nhttps://example.org");
  const [results, setResults] = useState([]);
  async function submit(event) {
    event.preventDefault();
    setResults(await runRequests(urls.split("\n").filter(Boolean)));
  }
  return <main><h1>URL request runner</h1><form onSubmit={submit}>
    <textarea rows="6" cols="60" value={urls} onChange={(e) => setUrls(e.target.value)} />
    <button>Run sequentially</button></form><RequestResults results={results} /></main>;
}
