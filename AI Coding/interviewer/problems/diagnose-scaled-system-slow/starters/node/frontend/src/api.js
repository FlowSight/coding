const API_URL = import.meta.env.VITE_API_URL ?? '/api';

export async function summarizeIncident(samples, thresholdMs) {
  const response = await fetch(`${API_URL}/diagnostics/summary`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ samples, thresholdMs })
  });
  if (!response.ok) throw new Error('Could not summarize incident');
  return response.json();
}
