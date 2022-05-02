// Handles the consumption of energy drinks / foods
// TODO: Make this work on Player.Consume() and give partial energy as the quantity is consumed instead of just 1 hit of energy at the end
modded class ActionForceConsume : ActionContinuousBase
{
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);

		ItemBase item = action_data.m_MainItem;
		if (item && item.GetQuantity() <= 0.01)
		{
			EnergyDrink drink = GetZenSleepConfig().GetEnergyDrink(action_data.m_MainItem.GetType());
			if (drink.ItemType != "")
			{
				float replenish = (float)action_data.m_Player.MAX_TIREDNESS * ((float)drink.EnergyGained / 100);
				PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());

				if (target)
				{
					target.InsertAgent(ZenSleep_Agents.TIREDNESS, -replenish);
				}
			}
		}
	}
}