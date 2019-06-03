using Oracle.ManagedDataAccess.Client;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiListTemplate
{
    class HrDAC
    {
        private string connectionString;
        private static readonly HrDAC instance = new HrDAC();

        private HrDAC()
        {
            //connectionString = Properties.Settings.Default.ConnectionString;
            connectionString = "DATA SOURCE=XE; User Id=c##hr;Password=tiger";
        }

        public static HrDAC Instance
        {
            get
            {
                return instance;
            }
        }

        public Employee GetEmployee(long id)
        {
            Employee employee = new Employee();
            string sql =
                "SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, EMAIL" +
                ", PHONE_NUMBER, HIRE_DATE, JOB_ID, SALARY, COMMISSION_PCT" +
                ", MANAGER_ID, DEPARTMENT_ID FROM EMPLOYEES WHERE EMPLOYEE_ID =:EMPLOYEE_ID";
            using (OracleConnection conn = new OracleConnection(connectionString))
            {
                OracleCommand cmd = new OracleCommand(sql, conn)
                {
                    CommandType = System.Data.CommandType.Text,
                    BindByName = true
                };
                cmd.Parameters.Add(":EMPLOYEE_ID", OracleDbType.Long).Value = id;
                conn.Open();

                using (OracleDataReader reader = cmd.ExecuteReader(CommandBehavior.SingleRow))
                {
                    if (reader.Read())
                    {
                        employee.Employee_id = reader.GetInt64(reader.GetOrdinal("EMPLOYEE_ID"));   // employee_id에 해당하는 인덱스가 몇 번인지 모르니까 getOrdinal로 데이터 가져옴
                        employee.First_name = reader.GetString(reader.GetOrdinal("FIRST_NAME"));
                        employee.Last_name = reader.GetString(reader.GetOrdinal("LAST_NAME"));
                        employee.Email = reader.GetString(reader.GetOrdinal("EMAIL"));
                        employee.Phone_number = reader.GetString(reader.GetOrdinal("PHONE_NUMBER"));
                        //employee.Phone_number = reader.IsDBNull(reader.GetOrdinal("PHONE_NUMBER")) ? "" : reader.GetString(reader.GetOrdinal("PHONE_NUMBER"));
                        employee.Hire_date = reader.GetDateTime(reader.GetOrdinal("HIRE_DATE"));
                        employee.Job_id = reader.GetString(reader.GetOrdinal("JOB_ID"));
                        employee.Salary = reader.GetDouble(reader.GetOrdinal("SALARY"));
                        employee.Commission_pct = reader.IsDBNull(reader.GetOrdinal("COMMISSION_PCT")) ? 0.0 : reader.GetDouble(reader.GetOrdinal("COMMISSION_PCT"));
                        employee.Manager_id = reader.IsDBNull(reader.GetOrdinal("MANAGER_ID")) ? 0 : reader.GetInt64(reader.GetOrdinal("MANAGER_ID"));
                        employee.Department_id = reader.IsDBNull(reader.GetOrdinal("DEPARTMENT_ID")) ? 0 : reader.GetInt32(reader.GetOrdinal("DEPARTMENT_ID"));
                    }
                }
            }

            return employee;
        }
        public List<Employee> GetEmployee()
        {
            List<Employee> employees = new List<Employee>();
            string sql =
                "SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, EMAIL" +
                ", PHONE_NUMBER, HIRE_DATE, JOB_ID, SALARY, COMMISSION_PCT" +
                ", MANAGER_ID, DEPARTMENT_ID FROM EMPLOYEES";
            //" WHERE EMPLOYEE_ID =:EMPLOYEE_ID";
            using (OracleConnection conn = new OracleConnection(connectionString))
            {
                OracleCommand cmd = new OracleCommand(sql, conn)
                {
                    CommandType = System.Data.CommandType.Text,
                    BindByName = true
                };
                conn.Open();

                using (OracleDataReader reader = cmd.ExecuteReader(CommandBehavior.Default))
                {
                    while (reader.Read())
                    {
                        Employee employee = new Employee();
                        employee.Employee_id = reader.GetInt64(reader.GetOrdinal("EMPLOYEE_ID"));   // employee_id에 해당하는 인덱스가 몇 번인지 모르니까 getOrdinal로 데이터 가져옴
                        employee.First_name = reader.GetString(reader.GetOrdinal("FIRST_NAME"));
                        employee.Last_name = reader.GetString(reader.GetOrdinal("LAST_NAME"));
                        employee.Email = reader.GetString(reader.GetOrdinal("EMAIL"));
                        employee.Phone_number = reader.GetString(reader.GetOrdinal("PHONE_NUMBER"));
                        //employee.Phone_number = reader.IsDBNull(reader.GetOrdinal("PHONE_NUMBER")) ? "" : reader.GetString(reader.GetOrdinal("PHONE_NUMBER"));
                        employee.Hire_date = reader.GetDateTime(reader.GetOrdinal("HIRE_DATE"));
                        employee.Job_id = reader.GetString(reader.GetOrdinal("JOB_ID"));
                        employee.Salary = reader.GetDouble(reader.GetOrdinal("SALARY"));
                        employee.Commission_pct = reader.IsDBNull(reader.GetOrdinal("COMMISSION_PCT")) ? 0.0 : reader.GetDouble(reader.GetOrdinal("COMMISSION_PCT"));
                        employee.Manager_id = reader.IsDBNull(reader.GetOrdinal("MANAGER_ID")) ? 0 : reader.GetInt64(reader.GetOrdinal("MANAGER_ID"));
                        employee.Department_id = reader.IsDBNull(reader.GetOrdinal("DEPARTMENT_ID")) ? 0 : reader.GetInt32(reader.GetOrdinal("DEPARTMENT_ID"));

                        employees.Add(employee);
                    }
                }
            }

            return employees;
        }

    }
}
