const API_URL = import.meta.env.VITE_API_URL ?? '/api';
export async function calculateMaximumInvitations(grid) {
  const response = await fetch(`${API_URL}/invitations/maximum`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ grid })
  });
  if (!response.ok) throw new Error('Invitation matching failed');
  return response.json();
}
