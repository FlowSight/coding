import React from'react';export default function RequestTimeline({events}){return <ul>{events.map((e,i)=><li key={i}>{e.timestampMillis}: {e.allowed?'allowed':'limited'}</li>)}</ul>}
