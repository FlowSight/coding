import { useState } from "react";
import { attempt } from "./api";
import DecisionLog from "./components/DecisionLog";

export default function App() {
  const [timestamp, setTimestamp] = useState("");
  const [decisions, setDecisions] = useState([]);
  async function submit(event) {
    event.preventDefault();
    const decision = await attempt(timestamp);
    setDecisions((items) => [...items, decision]);
  }
  return <main><h1>Sliding-window limiter</h1><form onSubmit={submit}>
    <input type="datetime-local" value={timestamp} onChange={(e) => setTimestamp(e.target.value)} />
    <button>Attempt request</button>
  </form><DecisionLog decisions={decisions} /></main>;
}
