<script>
  import Card from "./Card.svelte";

  export let port;
  export let portNum;

  let portData = new Int8Array(port);
</script>

<style>
  .portNum {
    padding-top: 10.5rem;
  }
</style>

<Card unconnected={portData[0] === 0}>
  <div class="portNum">{portNum}</div>
</Card>
