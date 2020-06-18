<script>
  import Port from "./Port.svelte";
  import Row from "./Row.svelte";

  export let ports;
</script>

<Row>
  {#each ports as port, portNum}
    <Port {port} {portNum} />
  {/each}
</Row>
