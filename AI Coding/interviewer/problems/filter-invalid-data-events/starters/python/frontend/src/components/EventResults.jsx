export default function EventResults({ events }) {
  return <pre>{JSON.stringify(events, null, 2)}</pre>;
}
