export async function filterEvents(events) {
  const response = await fetch('http://localhost:8080/api/events/filter', {method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(events)});
  if (!response.ok) throw new Error('Filtering failed'); return response.json();
}
