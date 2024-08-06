# Lazy Generic Async Actions Plugin

## Overview

The Lazy Generic Async Actions Plugin is a collection of asynchronous actions designed to simplify common tasks in Unreal Engine development. This plugin provides a set of flexible, easy-to-use Blueprint nodes that can be used to create more responsive and efficient game logic.

## Features

Currently, the plugin includes the following async actions:

1. **Delayed Action with Progress**
   - Performs a delayed action with periodic progress updates.
   - Useful for creating loading screens, cooldown timers, or any time-based progression.

2. **Wait on Actor Apex**
   - Detects when an actor reaches its highest point (apex) and when it starts descending.
   - Perfect for creating responsive gameplay mechanics based on object movement.

## Installation

1. Clone or download this repository.
2. Copy the plugin folder into your Unreal Engine project's `Plugins` directory.
3. Restart the Unreal Engine Editor if it's currently running.
4. Enable the plugin in your project settings.

## Usage

### Delayed Action with Progress

```cpp
UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Lazy Async Action")
static UAsyncLazyDelayedAction* AsyncDelayActionWithProgress(UObject* WorldContextObject, float DelayDuration, float UpdateInterval = 0.1f);
```

Use this node in your Blueprint to create a delayed action. You can specify the total duration and how often you want to receive progress updates.

### Wait on Actor Apex

```cpp
UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Lazy Async Action")
static UAsyncLazyWaitOnActorApex* AsyncCheckActorApex(UObject* WorldContextObject, AActor* ActorToCheck, float CheckInterval = 0.1f);
```

Use this node to monitor an actor's vertical movement. It will notify you when the actor reaches its highest point and when it starts descending.

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Support

If you encounter any issues or have questions, please file an issue on the GitHub repository.

## Acknowledgements

Special thanks to all contributors and users of this plugin.

---
## License

Copyright (C) 2024 Job Omondiale - All Rights Reserved.

This plugin is licensed under the BSD-3-Clause license found in the
LICENSE file in the root directory of this source tree.
