export function AcceptedEvents({ events }) {
  return <section><h2>Accepted events</h2>
    {events.length === 0 ? <p>No accepted events yet.</p> :
      <ul>{events.map((event) => <li key={event.id}>{event.id} at {event.timestamp}</li>)}</ul>}
  </section>;
}
