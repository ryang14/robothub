<script>
  import Card from "./Card.svelte";

  // Widgets for different devices
  import Motor from "./Motor.svelte";

  export let port;
  export let portNum;

  let portData = new Int8Array(port);
  let deviceType = portData[0];

  // Device to widget map
  let widgets = new Map();
  widgets.set(10, Motor);
</script>

<Card unconnected={deviceType === 0}>
  <div>Port: {portNum}</div>
  
  {#if widgets.has(deviceType)}
    <svelte:component this={widgets.get(deviceType)} port={portData} />
  {/if}
</Card>
