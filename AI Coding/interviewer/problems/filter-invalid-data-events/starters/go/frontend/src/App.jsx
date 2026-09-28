import { useState } from "react";
import { filterEvents } from "./api";
import EventReview from "./components/EventReview";

const sample = [{ id: "b", type: "created", payload: { version: "first" } }, { id: "a", type: "updated", payload: { version: "one" } }, { id: "b", type: "updated", payload: { version: "second" } }];
export default function App() {
  const [events, setEvents] = useState([]);
  return <main><h1>Event intake review</h1><button onClick={async () => setEvents(await filterEvents(sample))}>Validate batch</button><EventReview events={events} /></main>;
}
