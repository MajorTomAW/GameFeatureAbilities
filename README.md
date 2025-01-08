# Game Feature Abilities
Game feature actions to support modular use of the gameplay abilities system.

Depends on [Game Features Extension](https://github.com/MajorTomAW/GameFeatureExtension)

<a name="top"></a>
## Game Feature Actions
- **[Add Gameplay Cue Path](#UGameFeatureAction_AddGameplayCuePath)**
- **[Add Abilities](#UGameFeatureAction_AddAbilities)**


 
<a name="UGameFeatureAction_AddGameplayCuePath"></a>
## Add Gameplay Cue Path
⬆️ _[Back to Top](#top)_

Adds additional directories that are under the same directory as the owning
(GameFeature-) Asset to the GameplayCueManager's search path.   
Those directories will be added the moment your GameFeature is registered and removed when it is unregistered.

<img src="https://github.com/user-attachments/assets/609ac7e6-6454-47db-8b60-2d3ff16ca827" width="512px" alt="Game Feature Action: Add Gameplay Cue Path"/> 
 
> 📝After adding a new directory to the search path, the GameplayCueManager will not automatically update.    
> Which means you need to restart the editor to apply the changes.



<a name="UGameFeatureAction_AddAbilities"></a>
## Add Abilities
⬆️ _[Back to Top](#top)_

Adds abilities and attributes to the owning actor.
