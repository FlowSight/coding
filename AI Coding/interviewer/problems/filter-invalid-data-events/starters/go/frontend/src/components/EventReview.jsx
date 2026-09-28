export default function EventReview({ events }) {
  return <ul>{events.map((event) => <li key={event.id}><strong>{event.id}</strong> — {event.type} ({event.payload?.version})</li>)}</ul>;
}
