import { useState } from "react";
import { maximumInvitations } from "./api";
import CompatibilityMatrix from "./components/CompatibilityMatrix";

const grid = [[1, 1], [1, 0]];
export default function App() {
  const [count, setCount] = useState(null);
  return <main><h1>Invitation matcher</h1><CompatibilityMatrix grid={grid} /><button onClick={async () => setCount(await maximumInvitations(grid))}>Find maximum</button>{count !== null && <p>Accepted invitations: {count}</p>}</main>;
}
