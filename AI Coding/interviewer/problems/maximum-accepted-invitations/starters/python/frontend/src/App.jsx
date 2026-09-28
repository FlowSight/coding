import { useState } from "react";
import { calculateMaximum } from "./api";
import MatchSummary from "./components/MatchSummary";

export default function App() {
  const [grid, setGrid] = useState("[[1,1],[1,0]]");
  const [count, setCount] = useState(null);
  async function submit(event) {
    event.preventDefault();
    setCount((await calculateMaximum(JSON.parse(grid))).count);
  }
  return <main><h1>Invitation matcher</h1><form onSubmit={submit}>
    <textarea rows="6" cols="50" value={grid} onChange={(e) => setGrid(e.target.value)} />
    <button>Calculate maximum</button></form><MatchSummary count={count} /></main>;
}
