export function DecisionLog({ decisions }) {
  return <section><h2>Decision log</h2><ol>
    {decisions.map((decision, index) =>
      <li key={`${decision.now}-${index}`}>{decision.now}: {decision.allowed ? 'allowed' : 'blocked'}</li>)}
  </ol></section>;
}
