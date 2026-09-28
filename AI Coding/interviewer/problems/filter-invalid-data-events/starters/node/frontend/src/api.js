const API_URL = import.meta.env.VITE_API_URL ?? '/api';
export async function filterEvents(events) {
  const response = await fetch(`${API_URL}/events/filter`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ events })
  });
  if (!response.ok) throw new Error('Event filtering failed');
  return response.json();
}
