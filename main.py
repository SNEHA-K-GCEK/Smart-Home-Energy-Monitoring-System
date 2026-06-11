from python_simulation.alerts import check_alert
from python_simulation.cost_calculator import calculate_cost
from python_simulation.energy_calculator import calculate_energy
from python_simulation.energy_simulator import generate_data
from python_simulation.logger import save_data
from python_simulation.power_calculator import calculate_power
# Import the new Phase 9 module
from reports.report_generator import generate_pdf

# 1. Generate core system readings
voltage, current = generate_data()
power = calculate_power(voltage, current)
hours = 5
energy = calculate_energy(power, hours)
cost = calculate_cost(energy)
alert_status = check_alert(power)

# 2. Append metrics row to the CSV data log
save_data(voltage, current, power, energy, cost, alert_status)

# 3. Trigger Phase 9 PDF compilation
generate_pdf()