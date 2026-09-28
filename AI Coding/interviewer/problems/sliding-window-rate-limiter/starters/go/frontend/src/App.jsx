import { useState } from "react";
import { requestDecision } from "./api";
import DecisionHistory from "./components/DecisionHistory";

export default function App() {
  const [history, setHistory] = useState([]);
  async function send() {
    const at = new Date().toISOString();
    const allowed = await requestDecision(at);
    setHistory((items) => [...items, { at, allowed }]);
  }
  return <main><h1>Traffic limiter</h1><button onClick={send}>Send request</button><DecisionHistory history={history} /></main>;
}
